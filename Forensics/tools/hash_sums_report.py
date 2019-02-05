from forensics_modules.hash import get_hashes
from datetime import datetime
import argparse
import time
import os

CHUNK_SIZE = 2**20

parser = argparse.ArgumentParser(description="Forensics Hash Sums Report Tool")
parser.add_argument("report_name", help="Report name")
parser.add_argument("scandir", help="Root directory for scanning")
parser.add_argument("-v", action="store_true", help="verbose mode")
args = parser.parse_args()

class HashSumsReport():
    def __init__(self, report_name, scandir):
        self.report_name = report_name
        self.scandir = scandir
        self.time_now_timestamp = str(int(time.time()))
        self.time_now_isoformat = datetime.now().isoformat()

    def scan(self):
        empty = True
        print("[*] Scanning started on: \"%s\"" % self.scandir)
        report_file_csv = open("%s.csv" % self.report_name, "wb")
        report_file_csv.write(b"BASEDIR,FILENAME,MD5,SHA256\n")
        count_files = 0
        count_dirs = 0
        for root, dirs, files in os.walk(self.scandir):
            empty = False
            count_dirs += len(dirs)
            for f in files:
                count_files += 1
                if args.v:
                    print("\rFiles: %s, Dirs: %s" % (count_files,count_dirs), end="")
                filepath = os.path.join(root, f)
                hashes = get_hashes(filepath, CHUNK_SIZE)
                sha256 = hashes["sha256"]
                md5 = hashes["md5"]
                line = "%s,%s,%s,%s\n" % (root.replace(",", ""), f.replace(",", ""), md5, sha256)
                report_file_csv.write(line.encode("utf8"))
        report_file_csv.close()
        print("\n\n")
        if not empty:
            print("\n[+] Done")
        else:
            print("[!] This direcotry is empty or incorrect 'scandir' was given")
            print("[*] (on windows) if you try to scan disk use 'C:' instead of 'C:\\'")


scanner = HashSumsReport(args.report_name, args.scandir)
scanner.scan()
