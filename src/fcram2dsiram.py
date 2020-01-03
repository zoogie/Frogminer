import os,sys
offset=0

with open("fcram.mem","rb") as f:
	buf=f.read(0x4000000)

print("Dumping...")
with open("dsiram.bin","wb") as f:
	while offset < 0x4000000:
		f.write(buf[offset:offset+2])
		offset+=8
print("Done.")