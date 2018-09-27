import os,sys
from Cryptodome.PublicKey import RSA 
from Cryptodome.Signature import PKCS1_v1_5 
from Cryptodome.Hash import SHA1

def verify_sign(keys, signature, message, ppm):
	rsakey = RSA.importKey(keys) 
	signer = PKCS1_v1_5.new(rsakey) 
	digest = SHA1.new() 
	digest.update(message) 
	
	if signer.verify(digest, signature):
		print("ppm is already signed correctly!")
		return
	print("ppm sig is incorrect, let's sign it...")
	sigdump=signer.sign(digest)
	
	with open(sys.argv[1]+".bak","wb") as f:
		f.write(ppm)
	with open(sys.argv[1],"rb+") as f:
		f.write(message+sigdump+b"\x00"*0x10)
	print("\nFixed!\nOutput file: %s\nBackup file: %s.bak\nGero!" % (sys.argv[1],sys.argv[1]))

with open(sys.argv[1],"rb") as f:
	ppm=f.read()
	if b"\x50\x41\x52\x41" not in ppm[:4]:
		print("This is not a ppm file!")
		sys.exit(0)

size=len(ppm)
message=ppm[:size-0x90]
sig=ppm[size-0x90:size-0x10]

keys_pem="""-----BEGIN RSA PRIVATE KEY-----
MIICXAIBAAKBgQDCPLwTL6oSflv+gjywi/sM0TUB90xqOvuCpjduETjPoN2FwMeb
xNjdKIqHUyDu4AvrQ6BDJc6gKUbZ1E27BGZoCPH49zQRb+zAM6M9EjHwQ6BABr0u
2TcF7xGg2uQ9MBWz9AfbVQ91NjfrNWo0f7UPmffv1VvixmTk1BCtavZxBwIDAQAB
AoGAJqdTfjX0EG4Y/JMKZM/Wi/xuIhAGovVN6/gL+9lthtQqgV2V24fW6FwTBU8j
tKXdeVoh4Hr7nZ/ZO6wmM9tyTVSHo37XdF/1bsPM7iu/0M8A6+jJr94l6PYpCP5y
apPEj2RR154gTaVK7/J/OePZy6tRlgcI1awsqgCDcvweEsECQQD4KnxSdyJD0Oqa
xaIIhLkLZEuvkBmrLG+YQUezVOB60MjMC1DyIiZzc5otkQZ0RiopRm/57a6pXA58
1xSN9JiRAkEAyF5uvKCbA9+PORUn668W0N+uRWZ2+WaqC46HkUDnrVEa4FsnLsFD
0NlVmH2BXifPUPLMR6WzP+OJ9hKfve78FwJAQQJgLvomb716t7CuEa0zDFjpusP0
9XJeiXQQZFoHtCSddVZBjiyEBhpyeR1Uo4D96nIZQ0+QQa1r3ig5qjY5AQJAWvZD
324p8YA0TP3FucEq4ngpbWgu6tooqEZ0VQTaKFyBjwjSqO8kElQX/7o6WLxJ6b3P
71bSIVby8rtRubAc0QJBAJ1zhk7/d6PA4+J9aQ+jBi/OW+ljiD8yjatLq+4fqRfx
YsFzLqmzjxfiiX+6BzuHHcWJzBUmIcPyu+Y2N0BdT7M=
-----END RSA PRIVATE KEY-----
""" #huge greetz to martin korth and his gbatek docs for the pub/privkey locations!
verify_sign(keys_pem, sig, message, ppm)