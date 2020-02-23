# invoke SourceDir generated makefile for empty.pem3
empty.pem3: .libraries,empty.pem3
.libraries,empty.pem3: package/cfg/empty_pem3.xdl
	$(MAKE) -f C:\Users\admin\workspace_v9\Plantsensor/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\admin\workspace_v9\Plantsensor/src/makefile.libs clean

