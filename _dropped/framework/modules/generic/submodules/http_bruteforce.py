import requests


class HTTPBruteforce():

    def __init__(self):
        pass

    def http_basic_auth_bruteforce(self, url, logins,
                                   passwords, verbose=False, timeout=7):
        ret = []
        tries = len(logins) * len(passwords)
        progress_text = "\rBruteforcing: guessed:=%s, progress:=%.2f%%"
        c = 0.0
        for l_it, login in enumerate(logins):
            for p_it, password in enumerate(passwords):

                try:
                    req = requests.get(url, auth=(login, password),
                                       timeout=timeout)
                except Exception as e:
                    print("[-] Timeout occurred during basic http bruteforce")
                    return ret

                if req.status_code == 200:
                    ret.append((login, password))
                if verbose:
                    progress = (len(ret), 100*(c+1)/tries)
                    print(progress_text % progress, end="")
                    if l_it == len(logins) - 1 and p_it == len(passwords) - 1:
                        print("")
                    c += 1.0
        return ret
