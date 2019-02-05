from django.urls import path
from curation.views import SearchView

urlpatterns = [
    path('search/', SearchView.as_view(), name="curation-search")
]
