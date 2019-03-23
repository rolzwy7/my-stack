from typing import Dict, Tuple
import requests
import json

json.dumps()

# No typing
def make_get_request(url, headers):
    resp = requests.get(url, headers=headers)
    return resp.status_code, resp.content


status_code, content = make_get_request(
    "https://google.com", {"User-Agent": "lolz"})
print(status_code, content)


# Typing
def t_make_get_request(
    url: str,
    headers: Dict[str, str]
) -> Tuple[int, bytes]:
    resp = requests.get(url, headers=headers)
    return resp.status_code, resp.content


status_code, content = t_make_get_request(
    "https://google.com", {"User-Agent": "lolz"})
print(status_code, content)
