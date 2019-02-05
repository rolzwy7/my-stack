import requests
import json

import pprint as pp

# Error messages for this module
errmsg_cant_map_board = "[-] Couldn't map %s board: %s"
errmsg_cant_map_thread = "[-] Couldn't map %s thread: %s"

# Maps 4chan board's threads
# Parameters:
#     board - board name
def map_4chan_board(board):
    try:
        threads_json = json.loads(requests.get("http://a.4cdn.org/%s/threads.json" % board).content)
    except Exception as e:
        print(errmsg_cant_map_board % ("4chan", board))
        return []

    threads = [thread["threads"] for thread in threads_json]
    threads = [item["no"] for sublist in threads for item in sublist]
    return threads

# Maps 4chan thread's resources
#
# Parameters:
#     thread_link - link to the 4chan's thread
def map_4chan_thread(thread_link):
    try:
        result = requests.get(thread_link).content
    except Exception as e:
        print(errmsg_cant_map_thread % ("4chan", "%s/%s" % (board,thread_num)))
        return []

    ret = []
    for line in result.split(b"href=\""):
        if line.startswith(b"//i.4cdn.org"):
            ret.append(b"http:" + line.split(b"\"")[0])
    return ret
