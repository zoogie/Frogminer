#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <3ds.h>

#define menu_size 4

Result import(u64 tid, u8 op, u8 *workbuf, char *ext){
	Handle handle;
	Result res;
	FS_Path filePath;
	FS_Path archPath = { PATH_EMPTY, 1, (u8*)"" };
	char fpath[64]={0};
	uint16_t filepath16[256];
	ssize_t units=0;
	u32 len=255;
	
	memset(fpath, 0, 64);
	sprintf(fpath,"sdmc:/%08lX%s",(u32)tid, ext);
	memset(filepath16, 0, sizeof(filepath16));
	units = utf8_to_utf16(filepath16, (u8*)(fpath+5), len);
	
	filePath.type = PATH_UTF16;
	filePath.size = (units+1)*sizeof(uint16_t);
	filePath.data = (const u8*)filepath16;
	
	printf("import:%d %s\n", op, fpath);
	res = FSUSER_OpenFileDirectly(&handle, ARCHIVE_SDMC, archPath, filePath, FS_OPEN_READ, 0);
	printf("fsopen: %08X\n",(int)res);
	res = AM_ImportTwlBackup(handle, op, workbuf, 0x20000);
	printf("twl import: %08X %s\n\n",(int)res, res ? "FAILED!" : "SUCCESS!");
	FSFILE_Close(handle);
	
	return res;
}

Result export(u64 tid, u8 op, u8 *workbuf, char *ext){
	Result res;
	char fpath[256]={0};
	memset(fpath, 0, 128);
	sprintf(fpath,"sdmc:/%08lX%s",(u32)tid, ext);
	if(access(fpath, F_OK ) != -1 ) {
		printf("DS dlp already exists on SD\n");
		return 1;
	}
	printf("export:%d %016llX to %s\n", op, tid, fpath);
	res = AM_ExportTwlBackup(tid, op, workbuf, 0x20000, fpath);
	printf("twl export: %08X %s\n\n",(int)res, res ? "FAILED!" : "SUCCESS!");
	
	return res;
}

Result menuUpdate(int cursor){
	consoleClear();
	printf("Frogtool - zoogie\n\n");
	char menu[menu_size][128] = {
		"IMPORT  patched DS Download Play",
		"EXPORT  clean   DS Download Play",
		"RESTORE clean   DS Download Play",
		"BOOT    patched DS Download Play"
	};
	
	for(int i=0;i<menu_size;i++){
		printf("%s %s\n", cursor == i ? "->" : "  ", menu[i]);
	}
	
	printf("\nPress START to exit\n\n");
	
	return 0;
}

Result waitKey(){
	printf("\nTap bottom screen to continue ...\n");
	
	while(1){
		gspWaitForVBlank();
		gfxSwapBuffers();
		
		hidScanInput();
		u32 kDown = hidKeysDown();
		if(kDown & KEY_TOUCH) break;
	}
	
	return 0;
}

int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	u32 BUF_SIZE = 0x20000;
	u64 tid=0;
	u8 op=5;
	u32 SECOND=1000*1000*1000;
	int cursor=0;
	
	u8 *buf = (u8*)malloc(BUF_SIZE);
	Result res = nsInit();
	printf("nsInit: %08X\n",(int)res);
	res = amInit();
	printf("amInit: %08X\n\n",(int)res);
	svcSleepThread(1*SECOND);
	tid = 0x00048005484E4441;   //dlp
	//tid = 0x0004800542383841;
	//tid = 0x000480044b385545; 
	//tid = 0x000480044b454e4a; 
	
	menuUpdate(cursor);
	
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		if(kDown & KEY_A){
			switch(cursor){
				case 0: import(tid, op, buf, ".bin.patched"); break;
				case 1: export(tid, op, buf, ".bin"); break;
				case 2: import(tid, op, buf, ".bin"); break;
				case 3: printf("Booting dlp now ...\n");
						NS_RebootToTitle(0, tid); 
						while(1)gspWaitForVBlank();
				default:;
			}
			waitKey();
			menuUpdate(cursor);
		}
		else if(kDown & KEY_UP){
			cursor--;
			if(cursor<0) cursor=0;
			menuUpdate(cursor);
		}
		else if(kDown & KEY_DOWN){
			cursor++;
			if(cursor>=menu_size) cursor=menu_size-1;
			menuUpdate(cursor);
		}
		
	}

    free(buf);
	nsExit();
	amExit();
	gfxExit();
	
	return 0;
}