import os
from time import time
import hashlib


class AssetManager():

    def __init__(self, path_arr, temp=False, write=False, binary=True):
        if write and not temp: # write perm in assets/
            raise Exception("AssetManager can't write in assets directory")
        self.path_arr = path_arr
        self.temp = temp
        self.write = write
        self.binary = binary

        # random name for temp file
        if self.temp:
            temp_hash = hashlib.md5(str(time()).encode("utf8")).hexdigest()
            path_arr[-1] = path_arr[-1].split(".")[0] + "_%s.temp" % temp_hash

        self.init()

    def init(self):
        self.mode = "w" if self.write else "r"
        self.mode += "b" if self.binary else ""
        self.default_root = [os.environ["TEMP"]] if self.temp else ["assets"]
        self.path = self._ret_path(self.path_arr)
        self.file_handle = open(self.path, self.mode)

    def _ret_path(self, path_arr):
        return os.path.join(*(self.default_root + path_arr))

    def __str__(self):
        temp = "true" if self.temp else "false"
        path = self.path
        mode = self.mode
        ret = "AssetManager: temp:=%s path:=%s mode:=%s" % (temp, path, mode)
        return ret

    def read(self):
        self.file_handle.read()

    def write(self, content):
        self.file_handle.write(content)

    def read(self):
        self.file_handle.read()

    def close(self):
        self.file_handle.close()

    def lines(self):
        nlstrips = [b"\r\n", b"\n"] if self.binary else ["\r\n", "\n"]
        return [line.strip(nlstrips[0]).strip(nlstrips[1]) for line in self.file_handle]
