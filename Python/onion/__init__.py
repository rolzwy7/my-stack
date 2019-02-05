##Python3.5.1
##Windows 8.1 Pro
##Tor manual: https://www.torproject.org/docs/tor-manual.html.en


## Example torrc file configuration

##DataDirectory E:\Tor Browser\Browser\TorBrowser\Data\Tor
##GeoIPFile E:\Tor Browser\Browser\TorBrowser\Data\Tor\geoip
##GeoIPv6File E:\Tor Browser\Browser\TorBrowser\Data\Tor\geoip6
##HiddenServiceStatistics 0
##
##SocksPort 9150 IPv6Traffic PreferIPv6 KeepAliveIsolateSOCKSAuth
##ControlPort 9151
##CookieAuthentication 1
##
###JmwVyfFXJ3LjZUs9drtpt663AVr6cN4h3tP6ztQWrEdchnU8
##HashedControlPassword 16:6C0FADC9C6C7A51560FCA22399129702F1E994CB9CC51F90A087CAB0E3
import socket
import socks
import os
import time
import pdb
import socks
import requests
   
mainSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

class Tor():
    ipcheck_url = "http://checkip.amazonaws.com"
    original_ip = None
    current_endpoint = None
    tor_server_ip = "127.0.0.1"
    tor_server_port = 9150
    tor_server_port_control = 9151
    authentication_password = None

    def __init__(self, auth):
        self.authentication_password = auth
        
        print("Tor requests: %s:%s" % (self.tor_server_ip, self.tor_server_port))
        print("Tor command: %s:%s" % (self.tor_server_ip, self.tor_server_port_control))

        self.original_ip = self.check_end_ip()
        print("Original* IP: %s" % self.original_ip)

        self.connect_tor()
        self.current_endpoint = self.check_end_ip()
        print("Tor current endpoint: %s\n" % self.current_endpoint)
    
    def connect_tor(self):
        global mainSocket
        socks.setdefaultproxy(socks.PROXY_TYPE_SOCKS5, self.tor_server_ip, self.tor_server_port)
        socket.socket = socks.socksocket
        try:
            mainSocket.connect((self.tor_server_ip, self.tor_server_port_control))
            print("[+] Connected to Tor network")
        except Exception as e:
            print("[!] Check if everything is correct with your torrc file.")
            print("[-] Tor server isn't running or port specified isn't correct\n\terror:",e)
            exit(0)
        
    def disconnect_tor(self):
        socks.setdefaultproxy()

    def authenticate_tor(self):
        packet = 'AUTHENTICATE "%s"\n' % self.authentication_password
        mainSocket.send( packet.encode("utf8") )
        response = mainSocket.recv(128)
        if response.startswith(b'250'):
            return True
        else:
            print("[-] Authentication failed")
            return False
  
    def new_identity(self, force_new_endpoint=False):
        time.sleep(5)
        current_endpoint_copy = self.current_endpoint
        
        while True:
            if self.authenticate_tor():
                mainSocket.send(b'SIGNAL NEWNYM\n')
            self.current_endpoint = self.check_end_ip()
            if force_new_endpoint == True:
                if current_endpoint_copy == self.current_endpoint:
                    time.sleep(.3)
                    continue
                else:
                    print("[+] IP chain changed: %s => %s | force_new_endpoint" % (current_endpoint_copy, self.current_endpoint))
                    return True
            else:
                print("[+] IP chain changed: %s => %s" % (current_endpoint_copy, self.current_endpoint))
                return True
 
    def check_end_ip(self):
        return requests.get(self.ipcheck_url).text.strip("\n").strip("\r\n")

class TorRequests(Tor):
    session = None
    proxies = {}
    sockt_type = "socks5"
    
    def __init__(self):
        self.proxies["http"] = "%s://%s:%s" % (self.sockt_type, self.tor_server_ip, self.tor_server_port)
        self.proxies["https"] = "%s://%s:%s" % (self.sockt_type, self.tor_server_ip, self.tor_server_port)
        #print(self.proxies)
    
    def get(self, url):
        self.session = requests.session()
        self.session.proxies = self.proxies
        result = self.session.get(url)
        if result.status_code == 200:
            return result
        else:
            print("[-] Request failed:", url)
            return False

    def download(self, url, save_to=None):
        filename = url.split("/")[-1]
        
        if os.name == "nt":
            save_to = save_to.replace("/","\\")
        else:
            save_to = save_to.replace("\\","/")
        full_path = os.path.join(save_to, filename)

        self.session = requests.session()
        self.session.proxies = self.proxies
        pdb.set_trace()
        result = requests.get(url, stream=True)

        downaloded = 0
        with open(full_path, 'wb') as file_:
            for chunk in result.iter_content(chunk_size=1024):
                print("[+] Loop - tick")
                time.sleep(5)
                if chunk:
                    downaloded += len(chunk)
                    f.write(chunk)
                    print("\r[*] Downloading: %s | %s" % (filename, downaloded), end="")
            file_.close()
        return True


##object_ = Tor(auth="<AUTH_PASSWORD>")
##object_ = TorRequests()






