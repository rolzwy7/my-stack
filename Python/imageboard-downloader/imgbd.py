# TODO: Internet connection check
# TODO: Finish Whole board download

import imgbd_mapper as mapper
import imgbd_config as config
import imgbd_downloader as downloader
import argparse
import os
import time
import pprint as pp

parser = argparse.ArgumentParser(description='Imageboard downloader')
parser.add_argument('board', help='board name')
parser.add_argument('dest', help='destination')
parser.add_argument('--site', help='imageboard name (default: 4chan)')
parser.add_argument('--ban', nargs='+', help='extensions (divided by semicolon)')
parser.add_argument('--only', nargs='+', help='extensions (divided by semicolon)')
parser.add_argument('--thread', help='number of imageboard\'s thread')
args = parser.parse_args()

# Argparse validation
if args.only and args.ban:
    print("[-] Can't use ban and only switch together")
    exit(0)

# Encode extensions of 'ban' and 'only' argparse arguments (utf8)
if args.ban: args.ban = list(map(lambda x: x.encode("utf8"), args.ban))
if args.only: args.only = list(map(lambda x: x.encode("utf8"), args.only))

# DRY for 'ban' and 'only' check
#
# Parameters:
#   arr  - thread's array
# Returns:
#   Filtered arr
def ban_and_only(arr):
    if args.ban and not args.only:
        arr = [x for x in arr if x.split(b".")[-1] not in args.ban]
    elif args.only and not args.ban:
        arr = [x for x in arr if x.split(b".")[-1] in args.only]
    return arr

if __name__ == "__main__":
    # Imageboard name
    site = args.site if args.site else "4chan"
    # Single thread download
    if args.thread:
        print("[+] Downloading from single thread:", "%s/%s/%s\n" % (site, args.board, args.thread))
        thread_map = config.get_map_thread_function(site)(config.get_thread(site, args.board, args.thread))
        thread_map = ban_and_only(thread_map)
        counter = 0
        for resource in thread_map:
            try:
                downloader.download_synch(resource, args.dest)
                counter += 1
                print(
                    "\r[%s]" % time.asctime(), "downloaded:",
                    str(resource,"utf8"),
                    "| %.2f%%" % ( (counter/len(thread_map) * 100)),
                    end="\t"
                )
            except Exception as e:
                print(e)
            except KeyboardInterrupt:
                print("\n[*] User canceled downloading")
                exit(0)
        print("\n")
        exit(0)
    # Whole board download
    if not args.thread:
        print("[+] Mapping board:", "%s/%s\n" % (site, args.board))
        board_map = config.get_map_board_function(site)(args.board)
        board_map = list(map(lambda thread_num: config.get_thread(site, args.board, str(thread_num)), board_map))

        thread_map = []
        for thread in board_map:
            try:
                tmp_resources = config.get_map_thread_function(site)(thread)
                thread_map += tmp_resources
                print("[%s]" % time.asctime(),thread, "| resources:", len(tmp_resources))
            except KeyboardInterrupt:
                print("[*] User canceled operation")
                exit(0)

        thread_map = ban_and_only(thread_map)

        # pp.pprint(thread_map)
        print(len(thread_map))
        exit(0)
