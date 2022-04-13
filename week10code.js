// початкове налаштування сцени
function init() 
{
	scene = new THREE.Scene(); // створення сцени ("система")

	var WIDTH = window.innerWidth, HEIGHT = window.innerHeight; // визначити розміри вікна

	renderer = new THREE.WebGLRenderer({antialias: true}); // створення рендереру

	renderer.setSize(WIDTH, HEIGHT); // масштабування холсту до розміру вікна

	document.body.appendChild(renderer.domElement); // створення у документі HTML полотна (canvas)

	camera = new THREE.PerspectiveCamera(45, WIDTH/HEIGHT, 0.1, 20000); // кут огляду - 45 гр., поле зору [0.1; 20000]

	camera.position.set(0, 6, 0); // підняти камеру

	scene.add(camera); // розміщення камери на сцені

	window.addEventListener('resize', function() { // обробник події зміни розміру вікна
		var WIDTH = window.innerWidth, HEIGHT = window.innerHeight; // визначити розміри вікна
		renderer.setSize(WIDTH, HEIGHT); // масштабування холсту до нового розміру вікна
		camera.aspect = WIDTH/HEIGHT; // зміна співвідношення сторін
		camera.updateProjectMatrix();
	});

	renderer.setClearColor(0x333F47, 1); // встановити колір фону холсту: R (0x33), G (0x3f), B (0x47)

	var light = new THREE.PointLight(0xffffff); // створення точкового джерела світла білого кольору
	light.position.set(-100, 200, 100);
	scene.add(light); // розміщення точкового джерела світла білого кольору на сцені

	const texture = new THREE.TextureLoader().load( 'Screenshot from 2022-04-13 16-41-45.png' );

	var cylgeometry = new THREE.CylinderGeometry(3, 3, 7, 7); // циліндр довжиною 7, радіусом 3, 7-гранний зріз
	var cylmaterial = new THREE.MeshLambertMaterial( { map: texture } ); // білий матеріал, що відбиває промені
	var cylmesh = new THREE.Mesh(cylgeometry, cylmaterial); // ...

	cylmesh.position.set(0.9, -5, -6);
	scene.add(cylmesh); // розміщення ціліндричного об'єкту на сцені

	controls = new THREE.OrbitControls(camera,renderer.domElement);
}



function animate()
{
	controls.update();
	requestAnimationFrame( animate );
	renderer.render( scene, camera );
}

