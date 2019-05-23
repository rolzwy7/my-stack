import requests


class HTTPStatusCodeDiscovery():

    def __init__(self, ip, port, ssl=False):
        protocol = "https" if ssl else "http"
        self.url = "%s://%s:%s" % (protocol, ip, port)

        self.all_results = []
        self.last_results = []

    def discover(self, paths, status_code, timeout=5, quick=False):
        self.last_results = []
        ret = []
        for path in paths:
            url = "%s/%s" % (self.url, path)
            try:
                req = requests.get(url, timeout=timeout)
            except Exception as e:
                print("[-] Timeout occurred during http discover")
                return ret
            result = {"url": url, "status_code": req.status_code}
            self.all_results.append(result)
            self.last_results.append(result)
            if req.status_code == status_code:
                ret.append(result)
                if quick:
                    return result
        return ret
