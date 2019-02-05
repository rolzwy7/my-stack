import json
import os
import pprint as pp

_DEBUG = False

CONFIG_FILE_NAME = "config.json"
CONFIG_FILE_DIR = os.path.join(".")
CONFIG_PATH = os.path.join(
    CONFIG_FILE_DIR,
    CONFIG_FILE_NAME
)

class Config(object):

    config_file_found = False

    def debug_print(self, msg):
        print("[debug]", msg)

    def debug_info(self):
        print("\n")
        print("[ Debug Info ]")
        print("CONFIG_FILE_NAME :", CONFIG_FILE_NAME)
        print("CONFIG_FILE_DIR  :", CONFIG_FILE_DIR)
        print("CONFIG_PATH      :", CONFIG_PATH)
        print("\n")

    def __init__(self):
        self._DEBUG = _DEBUG
        if self._DEBUG: self.debug_info();
        self.config_content_des = None
        self.config_content_ser = None
        self.config_path = CONFIG_PATH
        if not self.init(): exit(0);
        self.read_config()

    def init(self):
        with os.scandir(CONFIG_FILE_DIR) as it:
            for entry in it:
                if (entry.name == CONFIG_FILE_NAME) and (entry.is_file()):
                        self.config_file_found = True

        if not self.config_file_found:
            print("[-] Config file not found")
            return False

        return True

    def read_config(self):
        if self._DEBUG: self.debug_print("Read config - call()");
        with open(self.config_path, "rb") as source:
            self.config_content_ser = source.read()
            try:
                self.config_content_des = json.loads(self.config_content_ser, encoding="utf8")
            except Exception as e:
                print("Config file isn't recognized as JSON file:", self.config_path)
                print("Exception:", e)
                exit(0)
            if self._DEBUG: pp.pprint(self.config_content_des);
            source.close()

    def write_config(self):
        self._sync()
        with open(self.config_path, "wb") as dest:
            dest.write(self.config_content_ser.encode("utf8"))
            dest.close()

    def _sync(self):
        if self._DEBUG: self.debug_print("Syncing - sync()");
        self.config_content_ser = json.dumps(
            self.config_content_des,
            indent=4,
            sort_keys=True
        )

    def __setitem__(self, key, value):
        self.config_content_des[key] = value
        self._sync()

    def __getitem__(self, key):
        self._sync()
        return self.config_content_des[key]

    def __delitem__(self, key):
        self._sync()
        del self.config_content_des[key]
