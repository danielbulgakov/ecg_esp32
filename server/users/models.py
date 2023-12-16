from djongo import models


class CustomUser(models.Model):
    username = models.CharField(max_length=150)
    email = models.EmailField(unique=True)
    password = models.CharField(max_length=256)

    def __str__(self):
        return self.email
