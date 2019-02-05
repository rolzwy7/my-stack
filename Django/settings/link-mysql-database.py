DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'OPTIONS': {
            'sql_mode': 'STRICT_TRANS_TABLES',
        },
        'NAME': '<dbname>',
        'USER': '<user>',
        'PASSWORD': '<pwd>',
        'HOST': '<host>',
        'PORT': '<port>' # 3306
    }
}
