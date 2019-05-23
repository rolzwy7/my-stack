# Mandatory imports
from framework.validator.validator import Validator
import framework.validator.validators as V
import utils.print_utils as print_utils
from framework.modules.module_common import Description
from assets.asset_manager import AssetManager
# Mandatory imports End

# Submodules imports
import framework.modules.generic.submodules.strings as strings
from framework.modules.generic.submodules.http_bruteforce import HTTPBruteforce
# Submodules imports End

# Database
from database.MongoDB import MongoDB
# Database End

# Category specific imports
# <Category specific imports here>
# Category specific imports End

import hashlib
import time
import os
import requests
import re


class ModuleDatabase(MongoDB):
    def __init__(self):
        super(ModuleDatabase, self).__init__()

    def insert_dump(self, **kwargs):
        fields = ["filed01", "fiel02"]
        return self._insert_one(self.db.dev_collection, fields, **kwargs)


class Module(Description):

    def __init__(self):
        self.init()
        self.db = ModuleDatabase()
        self.add_option(
            "targets",
            opt_default_value=["127.0.0.1:8080"],
            opt_validators=[V.vld_ipv4_with_port],
            opt_type=str,
            opt_is_list=True,
            mandatory=True,
            help="List of targets"
        )
        self.add_option(
            "ssl",
            opt_default_value=False,
            opt_validators=[],
            opt_type=bool,
            opt_is_list=False,
            mandatory=False,
            help="SSL"
        )

    # Run module
    def run(self):
        if not self.validate():
            print_utils.time_print("Module run stopped")
            return False

    # Save results to database
    def save(self, **kwargs):
        self.db.insert_dump(**kwargs)

    # Check if target is vulnerable
    def is_vuln(self, **kwargs):
        return None, "<not_implemented>"
