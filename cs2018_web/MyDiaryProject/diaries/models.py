from django.db import models
import datetime

class Diary(models.Model):
    title= models.CharField(max_length=256)
    detail= models.CharField(max_length=1024, default= 'No content')
    created= models.CharField(max_length=256, default= datetime.datetime.now)
