import imgbd_mapper as mapper

errmsg_no_such_imageboard = "There is no such imageboard in configuration: %s"

# Map element (general example)
# Order of parameters matters
#
# "<site name>": {
#     "root": "http://domain/",
#     "board_catalog": "http://domain/<board name>/catalog",
#     "thread": "http://domain/<board name>/thread/<thread number>",
#     "cdn": "http://domain/<board name>/<resource name>"
#     "map_board_function": <map_board_function>,
#     "map_thread_function": <map_thread_function>
# }
imageboards = {
    "4chan": {
        "root": "http://www.4chan.org/",
        "board_catalog": "http://boards.4chan.org/%s/catalog",
        "thread": "http://boards.4chan.org/%s/thread/%s",
        "cdn": "http://i.4cdn.org/%s/%s",
        "map_board_function": mapper.map_4chan_board,
        "map_thread_function": mapper.map_4chan_thread
    }
}
# List from imageboards dictionary keys
imageboards_list = list(imageboards)

# Gets thread link.
#
# Parameters:
#     site       - site name
#     board      - board name
#     thread_num - thread number
# Returns:
#     Link to board's thread
def get_thread(site, board, thread_num):
    if site not in imageboards_list:
        raise ValueError(errmsg_no_such_imageboard % site)
    return imageboards[site]["thread"] % (board, thread_num)

# Gets board catalog.
#
# Parameters:
#     site        - site name
#     board       - board name
# Returns:
#     Link to board's catalog
def get_board_catalog(site, board):
    if site not in imageboards_list:
        raise ValueError(errmsg_no_such_imageboard % site)
    return imageboards[site]["board_catalog"] % (board)

# Gets resource link.
#
# Parameters:
#     site    - site name
#     board   - board name
#     name    - resouce name
# Returns:
#     Link to resource
def get_resource(site, board, name):
    if site not in imageboards_list:
        raise ValueError(errmsg_no_such_imageboard % site)
    return imageboards[site]["cdn"] % (board, name)

# Gets map thread function for given site.
#
# Parameters:
#     site    - site name
# Returns:
#     Function of thread mapping
def get_map_thread_function(site):
    if site not in imageboards_list:
        raise ValueError(errmsg_no_such_imageboard % site)
    return imageboards[site]["map_thread_function"]

# Gets map board function for given site.
#
# Parameters:
#     site    - site name
# Returns:
#     Function of board mapping
def get_map_board_function(site):
    if site not in imageboards_list:
        raise ValueError(errmsg_no_such_imageboard % site)
    return imageboards[site]["map_board_function"]
