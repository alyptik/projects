#!/usr/bin/env python

import fuse
import time
import sys
import errno

class fs(fuse.Operations):
    def getattr(self, path, fh=None):
        if "blockme" in path:
            print raw_input('blocked, press enter')
        raise fuse.FuseOSError(errno.ENOENT)

fuse.FUSE(fs(), sys.argv[1], foreground=True)
