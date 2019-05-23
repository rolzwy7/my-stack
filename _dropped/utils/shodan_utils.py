import shodan
import json
import os

SHODAN_API_KEY = os.environ["SHODAN_API_KEY"]

# Simple query - shodan api
def simple_query(query):
    ret = []
    api = shodan.Shodan(SHODAN_API_KEY.strip(""))
    result = api.search(query)
    for service in result["matches"]:
        ret.append( "%s:%s" % (service["ip_str"], service["port"]) )
    return ret

# Returns details about the host
def get_host(ip):
    # IP - without port
    api = shodan.Shodan(SHODAN_API_KEY.strip(""))
    ret = api.host(ip)
    return json.dumps(ret, indent=4, sort_keys=True)
