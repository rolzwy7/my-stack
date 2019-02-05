# all dirs served at /static/ with indexing off by default
STATICFILES_DIRS = [
    os.path.join(BASE_DIR, "static_dev")
]

# target of manage.py collectstatic
STATIC_ROOT = os.path.join(BASE_DIR, "static")
