# python manage.py shell
from django.contrib.sites.models import Site
Site.objects.create(name='website.com', domain='website.com')
