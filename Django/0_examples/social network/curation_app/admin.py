from django.contrib import admin
from . import models

class PasswordInline(admin.TabularInline):
    model = models.Password

@admin.register(models.IdentityCard)
class IdentityCardAdmin(admin.ModelAdmin):
    date_hierarchy = 'date_modified'
    list_display = ('__str__', 'given_names', 'surname')

@admin.register(models.Password)
class PasswordAdmin(admin.ModelAdmin):
    date_hierarchy = 'date_modified'
    list_display = ('__str__', 'verified', 'username', 'password')
    search_fields = ('username', 'password')
    list_filter = ('verified', 'service__name')
    actions = ["mark_verified", "mark_unverified"]

    def mark_verified(self, request, queryset):
        queryset.update(verified=True)

    def mark_unverified(self, request, queryset):
        queryset.update(verified=False)

@admin.register(models.Service)
class ServiceAdmin(admin.ModelAdmin):
    list_display = ('name', 'url')
    search_fields = ('name', 'url')

@admin.register(models.Person)
class PersonAdmin(admin.ModelAdmin):
    date_hierarchy = 'date_modified'
    inlines = [PasswordInline]
    list_display = ('__str__', 'gender', 'birthday')
    search_fields = ('first_name', 'last_name')

@admin.register(models.Document)
class DocumentAdmin(admin.ModelAdmin):
    date_hierarchy = 'date_modified'
    list_display = ('__str__', 'sha256')

@admin.register(models.Image)
class ImageAdmin(admin.ModelAdmin):
    date_hierarchy = 'date_modified'
    list_display = ('__str__', 'sha256')

@admin.register(models.Relation)
class RelationAdmin(admin.ModelAdmin):
    date_hierarchy = 'date_modified'
    list_display = ('person_first', 'name_first', 'person_second', 'name_second')
    search_fields = (
        'person_first__first_name',
        'person_first__last_name',
        'person_second__first_name',
        'person_second__last_name',
    )
