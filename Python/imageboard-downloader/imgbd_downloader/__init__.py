from threading import Thread
from requests.exceptions import Timeout, HTTPError
import requests
import os

g_max_thread_number = 5
g_exts_banned = []

# Synchronous download for small files
#
#
def download_synch(resource, dest):
    try:
        res = requests.get(resource, timeout=5)
        if res.status_code == 404:
            raise HTTPError("[-] Resource 404'd : %s" % resource)
    except Timeout:
        raise Timeout("[-] Timeout for synchronous download: %s" % resource)
    except Exception as e:
        raise Exception
    filename = str(resource.split(b"/")[-1], "utf8")
    filepath = os.path.join(dest, filename)
    with open(filepath, "wb") as file:
        file.write(res.content)
        file.close()

# Queues resource objects for downloading
#
# Parameters:
#   resource - Resource<class> object
def queue_downloads(resources):
    pass
