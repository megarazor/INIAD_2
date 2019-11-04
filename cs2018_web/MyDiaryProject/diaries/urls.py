from django.urls import path
from . import views

urlpatterns = [
    path(r'', views.top),
    path(r'diaries', views.index, name='index'),
    path(r'diaries/<int:diary_id>/', views.detail, name='detail'),
    path(r'diaries/create/', views.create, name='create'),
    path(r'diaries/update/<int:diary_id>/', views.update, name='update'),
    
]