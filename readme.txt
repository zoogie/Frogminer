FROGminer Beta Test 

What is this?
tl;dr ~ Free CFW for USA, EUR, JPN ~

!tl;dr - This differs from previous iterations of seedminer in that homebrew, instead of System Settings, is used to import/export the dsiware (this eases size restrictions). 
Also, eshop dsiware is not needed or used this time. Instead, a different dsihax game, flipnote studio JPN v0, is injected into an internal dsi system app.
This particular v0 of flipnote is needed because all 4 other regions/versions throw an error and kick you back to home menu if it cannot find its
save file on NAND. System dsiware titles do not have saves and you cannot import a modified system dsiware that has one.

Needed files:
boot.nds 			https://github.com/zoogie/b9sTool/releases/latest - put this on the sd root
Frogtool.3dsx 		included - put this in your sdmc:/3DS folder
private/			included - drag this directory to the root of your sd card - this is the flipnote exploit file
srl.nds				This is the Flipnote Studio JPN v0 file. MD5 362e288964d8228f4025be4f34a26529 filename "Ugoku Memo Chou (Japan).nds"
					This file is copyrighted so you have to find it on your own!
TADpole (offline)	https://github.com/zoogie/TADpole/releases Note: Online services like https://jisagi.github.io/TADpole-Online/
					and https://jenkins.nelthorya.net/job/DSIHaxInjector/ are not currently supported as this exploit method is brand new. Give it time.
					FROGminer should also be added to 3ds.guide in due time after the beta.
movable.sed			Get this from the steelminer process linked below
src/				Everything in this folder can be ignored by end users

1. Get Steel Diver: Sub Wars and do the steelminer process at the link below. Save your movable.sed!
http://steelminer.jisagi.net/

2. EXPORT your DS Download Play with Frogtool.3dsx (484E4441.bin on sd root). exit the app by pressing start.

3. Use the offline TADpole program to dump 484E4441.bin then inject Flipnote Studio JPN v0 into it, then rebuild it.
	a. place the movable.sed you got from the steelminer process inside the TADpole/resources folder. Copy and paste 484E4441.bin in the TADpole folder.
	   Don't cut or move the 484E4441.bin file from the sd card as this is the clean version of DS dlp that you will need to RESTORE the app post hax installation (optional).
	a. drop the 484E4441.bin on _dump.bat
	b. place the srl.nds file into the 484E4441 directory and overwrite the existing file
	c. drop the 484E4441.bin on _rebuild.bat again. this will create 484E4441.bin.patched
	No save file is needed. It will mess things up so don't inject one. The srl size will increase - that's alright.

4. Copy the patched DS download play (484E4441.bin.patched) back to your sd card. Don't rename it. IMPORT it back with FROGtool.3dsx.

5. Use the app to BOOT DS download play (now infused with frog power) and perform the custom FROGminer ugopwn exploit.
Demonstration (the steps are a bit different from regular flipnote lenny process):
https://streamable.com/ti9jk

6. You should now be running b9sTool.
Continue on at:
https://3ds.hacks.guide/installing-boot9strap-(dsiware-game-injection)#section-v---flashing-the-target-3dss-firm


Thanks:
Martin Korth (nocash) - location hints for flipnote privkeys, no$gba, excellent Gbatek docs. I could go on.
Shutterbug2000 - ugopwn exploit. brilliant stuff!
Fincs and Wintermute - Flipnote Lenny, a revised version of ugopwn. This is the version I ported. Very clean, elegant work which made it a more manageable task for me.
zacchi4k and Chromaryu - for tools assistance, thanks a bunch!
All my peeps on the Nintendo Homebrew Discord and GBAtemp for constant support of seedminer and its users!

Gero!