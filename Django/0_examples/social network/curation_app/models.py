from django.db import models
from django.db.models import Q
from datetime import datetime
import hashlib

# Helpers
from .victools.models import model_save_tools

class IdentityCard(models.Model):
    """
    Stores identity card record
    """
    date_added = models.DateField(auto_now_add=True)
    date_modified = models.DateField(auto_now=True)

    GENDERS = (('M', 'Male'),('F', 'Female'))

    surname = models.CharField(max_length=64, blank=True, null=True)
    given_names = models.CharField(max_length=64, blank=True, null=True)
    family_name = models.CharField(max_length=64, blank=True, null=True)
    parents_given_names = models.CharField(max_length=64, blank=True, null=True)
    date_of_birth = models.DateField(blank=True, null=True)
    gender = models.CharField(max_length=1, choices=GENDERS, blank=True, null=True)
    pesel = models.CharField(max_length=11, blank=True, null=True, unique=True)
    card_number = models.CharField(max_length=16, blank=True, null=True, unique=True)
    date_of_issue = models.DateField(blank=True, null=True)
    date_of_expiry = models.DateField(blank=True, null=True)
    issuing_authority = models.CharField(max_length=64, blank=True, null=True)

    def __str__(self):
        return "%s / %s" % (self.pesel, self.card_number)

    class Meta:
        verbose_name_plural = "Identity Cards"

    def save(self, *args, **kwargs):
        model_save_tools.modify_self_identity_card(self)
        super().save(*args, **kwargs)

class Service(models.Model):
    """
    Stores web service record
    """
    date_added = models.DateField(auto_now_add=True)
    date_modified = models.DateField(auto_now=True)
    name = models.CharField(max_length=128, unique=True)
    url = models.URLField(blank=True, null=True, unique=True)

    def __str__(self):
        return self.name

    class Meta:
        verbose_name_plural = "Services"

class Password(models.Model):
    """
    Stores credentials record
    """
    date_added = models.DateField(auto_now_add=True)
    date_modified = models.DateField(auto_now=True)

    owner = models.ForeignKey('Person', null=True, on_delete=models.SET_NULL)
    service = models.ForeignKey('Service', null=True, on_delete=models.SET_NULL)

    verified = models.BooleanField(default=False)
    username = models.CharField(max_length=64, blank=True, null=True)
    password = models.CharField(max_length=256, blank=True, null=True)

    def __str__(self):
        return "%s: %s" % (self.service.name, self.username)

    class Meta:
        verbose_name_plural = "Passwords"

class Person(models.Model):
    """
    Stores basic information about person
    """
    GENDERS = (('M', 'Male'),('F', 'Female'))
    date_added = models.DateField(auto_now_add=True)
    date_modified = models.DateField(auto_now=True)

    id_card = models.ForeignKey('IdentityCard', null=True, blank=True, on_delete=models.SET_NULL)

    gender = models.CharField(max_length=1, choices=GENDERS, blank=True, null=True)
    first_name = models.CharField(max_length=30)
    middle_name = models.CharField(max_length=60, blank=True)
    last_name = models.CharField(max_length=30)
    birthday = models.DateField(blank=True, null=True)

    def __str__(self):
        return " ".join([self.first_name, self.middle_name, self.last_name])

    class Meta:
        verbose_name_plural = "People"

class Document(models.Model):
    """
    Stores document record
    """
    date_added = models.DateField(auto_now_add=True)
    date_modified = models.DateField(auto_now=True)

    owner = models.ForeignKey('Person', null=True, blank=True, on_delete=models.SET_NULL)
    upload = models.FileField(upload_to='documents/%Y/%m')
    name = models.CharField(max_length=128, null=True, blank=True)

    sha256 = models.CharField(max_length=64, null=True, blank=True, editable=False, unique=True)

    def __str__(self):
        return self.name

    class Meta:
        verbose_name_plural = "Documents"

    def save(self, *args, **kwargs):
        if self.upload and not self.name:
            name = self.upload.name
            self.name = name
        if self.upload._file:
            # Sha256
            file_content = self.upload.file
            sha256 = hashlib.sha256()
            sha256.update(file_content.read())
            self.sha256 = sha256.hexdigest()
        super().save(*args, **kwargs)

class Image(models.Model):
    """
    Stores image record
    """
    date_added = models.DateField(auto_now_add=True)
    date_modified = models.DateField(auto_now=True)

    owner = models.ForeignKey('Person', null=True, blank=True, on_delete=models.SET_NULL)
    image = models.ImageField(upload_to='images/%Y/%m')
    name = models.CharField(max_length=128, null=True, blank=True)

    sha256 = models.CharField(max_length=64, null=True, blank=True, editable=False, unique=True)
    width = models.CharField(max_length=10, null=True, blank=True, editable=False)
    height = models.CharField(max_length=10, null=True, blank=True, editable=False)

    def __str__(self):
        return self.name

    class Meta:
        verbose_name_plural = "Images"

    def save(self, *args, **kwargs):
        if self.image and not self.name:
            name = self.image.name
            self.name = name
        if self.image._file:
            # Width, Height
            w, h = self.image._file.image.size
            self.width = str(w)
            self.height = str(h)
            # Sha256
            file_content = self.image.file
            sha256 = hashlib.sha256()
            sha256.update(file_content.read())
            self.sha256 = sha256.hexdigest()
        super().save(*args, **kwargs)

class Relation(models.Model):
    """
    Stores relation record
    """
    RELATION_SELECT = [
        ('CHL', 'Child'), ('PAR', 'Parent'),
        ('HUS', 'Husband'), ('WIF', 'Wife'),
        ('SIB', 'Sibling'),
        ('FRI', 'Friend'),
        ('GFR', 'Girlfriend'), ('BFR', 'Boyfriend'),
        ('REL', 'Relative'),
        ('LOV', 'Lover'),
        ('UKN', 'Unknown')
    ]

    date_modified = models.DateField(auto_now=True)
    date_added = models.DateField(auto_now_add=True)

    person_first = models.ForeignKey("Person", null=True, blank=True, on_delete=models.SET_NULL,
        related_name='%(class)s_person_first')

    name_first = models.CharField(max_length=3, choices=RELATION_SELECT, null=True, blank=True)

    person_second = models.ForeignKey("Person", null=True, blank=True, on_delete=models.SET_NULL,
        related_name='%(class)s_person_second')

    name_second = models.CharField(max_length=3, choices=RELATION_SELECT, null=True, blank=True)

    def save(self, *args, **kwargs):
        model_save_tools.modify_self_relation(self)
        super().save(*args, **kwargs)

    class Meta:
        verbose_name_plural = "Relationships"
