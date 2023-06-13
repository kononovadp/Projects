from django.db import models
class districts(models.Model):
    districts = models.CharField("Назва області",max_length=40)