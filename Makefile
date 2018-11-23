FOLDERS = src app
.PHONY = all clean

all:
	@for d in $(FOLDERS);\
	do\
		$(MAKE) -C $$d;\
	done\

clean:
	@for d int $(FOLDERS);\
	do\
		$(MAKE) -C $$d clean;\
	done\
