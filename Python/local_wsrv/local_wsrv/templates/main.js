function cambiar_estado() {
    // Aquí hacemos la petición HTTP GET a la API
    fetch('/obtener_estado_boton/')
    .then(response => response.json())
    .then(data => {
        // Actualizamos el texto del botón en función del estado actual del botón
        let boton = document.getElementById('boton');
        boton.innerText = data.estado_boton ? 'Botón presionado' : 'Botón';
    })
    .catch(error => {
        console.error(error);
    });
}
