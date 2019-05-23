from datetime import datetime
import os

from texttable import Texttable


# MODULES_TYPES = {
#     "scanner":"scanner",
#     "exploit":"exploit",
#     "bruteforcer":"bruteforcer"
# }

# Prints message with current time
def time_print(msg, end="\n"):
    current_time = datetime.strftime(datetime.now(), "%Y-%m-%d %H:%M:%S")
    print("[%s]" % current_time, msg, end=end)


# Prints message with current time as progress
def time_print_progress(msg):
    current_time = datetime.strftime(datetime.now(), "%Y-%m-%d %H:%M:%S")
    print("\r[%s] %s" % (current_time, msg), end="")


# Clears screen
def clear_screen():
    func = "cls" if os.name == "nt" else "clear"
    os.system(func)


# Returns modules table for printing
def get_modules_search_table(search_term, _map):
    table = Texttable()
    # _map = get_modules_map()
    all_rows = []
    all_rows.append(["Id", "Type", "Name", "Description"])
    for v in _map:
        tmp_name = v['use_name']
        tmp_type = v['handle'].__info__["type"]
        tmp_description = v['handle'].__info__["description"]
        tmp_id = v['id']
        if search_term in tmp_name:
            all_rows.append(
                [tmp_id, tmp_type, tmp_name, tmp_description]
            )
        # import pdb; pdb.set_trace()
    table.add_rows(all_rows)
    if len(all_rows) > 1:
        ret = table.draw() + "\n"
    else:
        ret = "No results for: %s" % search_term
    return ret


# returns banner
def get_banner():
    banner = """

            noname

        """
    return banner
