import json

def json_decorator(func):
    def decorated(*args, **kwargs):
        result = func(*args, **kwargs)
        ret = {**kwargs, "result": result}
        return json.dumps(ret, indent=4, sort_keys=True)
    return decorated

@json_decorator
def add(x ,y):
    return x + y

print(add(x=1,y=2))
