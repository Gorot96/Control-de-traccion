from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
from rest_framework.decorators import api_view
from rest_framework.response import Response

estado_boton = False  # Estado inicial del botón

def index(request):
    if request.method == 'POST':
        # Aquí debes actualizar el estado del botón
        return HttpResponse('Botón presionado')
    else:
        return render(request, 'index.html')

@api_view(['POST'])
def guardar_estado_boton(request):
    global estado_boton
    if request.method == 'POST':
        data = request.POST
        estado_boton = data['estado_boton'] == 'presionado'
        return JsonResponse({'estado_boton': estado_boton})
    else:
        return JsonResponse({'error': 'Método no permitido'})