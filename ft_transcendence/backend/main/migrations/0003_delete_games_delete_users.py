# Generated by Django 4.2.10 on 2024-02-26 19:51

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('main', '0002_alter_games_player1'),
    ]

    operations = [
        migrations.DeleteModel(
            name='Games',
        ),
        migrations.DeleteModel(
            name='Users',
        ),
    ]
