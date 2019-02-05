from django import template
import time
register = template.Library()

@register.filter(name='precentage')
def precentage(value, arg):
    return "%.2f%%" % (float(value/arg)*100)

@register.filter(name="capitalize")
def capitalize(value, arg):
    return value.upper()

@register.filter(name="short_str")
def short_str(value, arg):
    if len(value) > arg:
        return "%s ..." % value[:arg]
    else:
        return value[:arg]

@register.filter(name="prepend")
def prepend(value, arg):
    return "%s%s" % (arg, value)

@register.filter(name="append")
def append(value, arg):
    return "%s%s" % (value, arg)

@register.filter(name="is_str_longer_then")
def is_str_longer_then(value, arg):
    if len(value) > arg:
        return True
    else:
        return False

@register.filter(name="list_len")
def list_len(value, arg):
    return len(value)

@register.filter(name="modulo_bool")
def modulo_bool(value, arg):
    if value % arg == 0:
        return True
    else:
        return False

@register.filter(name="timestamp_to_date")
def timestamp_to_date(value, arg):
    return datetime.fromtimestamp(value).strftime(arg)

@register.simple_tag
def dict_key_lookup(the_dict, key):
    if key in the_dict.keys():
        return the_dict[key]
    else:
        return ""

@register.filter(name="dict_key_lookup_dash")
def dict_key_lookup_dash(the_dict, key):
    return the_dict[key.replace("-", "_")]
