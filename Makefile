all:
	# PIC: position independent code (for shared object)
	gcc -fPIC -fno-stack-protector -c ajarpam.c
	ld -x --shared -o pam_ajar.so ajarpam.o
	# TODO: this depends..
	@echo "Copy pam_ajar.so to /lib/x86_64-linux-gnu/security/"
	@echo "Or.. to /lib/security/"
