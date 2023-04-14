from django.shortcuts import render
from django.http import HttpResponse

def index(request):
    if request.method == 'POST':
        # Aquí debes actualizar el estado del botón
        return HttpResponse('Botón presionado')
    else:
        return render(request, 'index.html')
