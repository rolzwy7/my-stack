import Utils as utils
import os

ENV_USED = {
    "USERPROFILE"    : "Configuration directory will be created here",
    "SHODAN_API_KEY" : "Provide your shodan api key: https://www.shodan.io",
    "TEMP"           : "All temporary files will be stored here",
}

# Checks if all declared windows system variables exist
def setup_check_envs_exists():
    for env_key, env_value in ENV_USED.items():
        try:
            os.environ[env_key]
        except KeyError:
            utils.time_print("Environment variable is missing: %s" % env_key)
            utils.time_print(env_value)
