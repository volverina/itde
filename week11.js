// початкові налаштування
function init() 
{
	scene = new THREE.Scene(); // <a-scene> - створення сцени

	var 	WIDTH = window.innerWidth, // внутрішня ширина вікна
		HEIGHT = window.innerHeight; // внутрішня висота вікна

	renderer = new THREE.WebGLRenderer({antialias: true}); // рендерер - перетворення тривімрного у двовимірне
	renderer.setSize(WIDTH, HEIGHT); // <canvas> - "розтягування" холста до розмірів вікна
	document.body.appendChild(renderer.domElement); // додавання холста до документа

	camera = new THREE.PerspectiveCamera(45, WIDTH/HEIGHT, 0.1, 20000); // створення перспективної камери з кутом зору 45 градусів, співвідношення сторін - як у вікна, поле зору = [0.1, 20000]
	scene.add(camera); // розміщуємо камеру на сцені
	camera.position.set(0, 6, 0);

	window.addEventListener(// користувацький обробник події
		'resize', // при зміні розміру вікна
		function() {
			var WIDTH = window.innerWidth, HEIGHT = window.innerHeight; // нові розміри вікна
			renderer.setSize(WIDTH, HEIGHT); // "розтягування" холста до розмірів вікна
			camera.aspect = WIDTH/HEIGHT; // співвідношення сторін - як у вікна
			camera.updateProjectMatrix(); // оновлення матриці проєктування 
		}
	);

	renderer.setClearColor(0x333F47, 1); // колір холста: R (0x33), G (0x3f), B (0x47)

	var light = new THREE.PointLight(0xffffff); // точкове джерело, білий колір
	light.position.set(-100, 200, 100);
	scene.add(light); // розміщуємо на сцені точкове джерело освітлення білого кольору

	var loader = new THREE.TextureLoader(); 

	var cylgeometry = new THREE.CylinderGeometry(3, 3, 7, 7); // циліндр з 7-гранною основою радіуса 3 довжиною 7
	var cylmaterial = new THREE.MeshLambertMaterial({map: loader.load('https://i.imgur.com/tD0lCkn.jpeg')}); // не відкидає тінь, колір - білий
	var cylmesh = new THREE.Mesh(cylgeometry, cylmaterial); 
	cylmesh.position.set(0.9, -5, -6);
	scene.add(cylmesh); // розміщуємо на сцені циліндр з 7-гранною основою радіуса 3 довжиною 7 (колір - білий)

	controls = new THREE.OrbitControls(camera,renderer.domElement);
}


// анімація
function animate() 
{
	controls.update();
	renderer.render(scene, camera); // проєкція: 3D -> 2D 
	requestAnimationFrame(animate); 
}

