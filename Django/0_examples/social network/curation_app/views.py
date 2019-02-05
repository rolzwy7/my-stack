from django.http import HttpResponse
from django.shortcuts import render
from django.views import View

class SearchView(View):
    template_name = "pages/search.html"
    def get(self, request):
        return render(request, self.template_name, {})
