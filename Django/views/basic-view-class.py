#views.py in app
from django.shortcuts import render
from django.views.generic import View

class Test(View):
    def get(self, request):
        return render(request, "Test.html", {"data":"test"})# Test.html is in app/templates/ directory

#urls.py in app
from . import views
urlpatterns = [
    path('test/', views.Test.as_view())
]

#urls.py in main app
urlpatterns = [
    path('admin/', admin.site.urls),
    path('app_route/', include("app.urls"))
]
