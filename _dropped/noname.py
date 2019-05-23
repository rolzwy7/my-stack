import argparse

from framework.framework import Framework
from framework import framework_intro
import utils.print_utils as print_utils

parser = argparse.ArgumentParser(description="Noname")
# parser.add_argument("--install", action="store_true", help="Install Camsploit")
args = parser.parse_args()

# setup_utils.setup_check_envs_exists()

# Framework CLI routine setup
print_utils.clear_screen()
Framework().cmdloop(intro=framework_intro())
