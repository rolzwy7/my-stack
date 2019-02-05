# https://docs.djangoproject.com/en/2.0/topics/auth/default
from django.utils.decorators import method_decorator
from django.contrib.auth.decorators import login_required



# Method decorator + login required
@method_decorator(login_required(login_url="/admin/"), name="get")
class DashboardView(View):
    template_name = "DashboardView.html"
    def get(self, request):
        data = {}
        return render(request, self.template_name, data)
