var arToolkitContext=false;


function init_three()
{
	renderer = new THREE.WebGLRenderer({antialias: true, alpha: true});
	//renderer.setClearColor(new THREE.Color('lightgrey'), 0);

	renderer.setSize(window.innerWidth, window.innerHeight); // <canvas> - "розтягування" холста до розмірів вікна
	document.body.appendChild(renderer.domElement); // додавання холста до документа

	scene = new THREE.Scene();
	// Create a camera
	camera = new THREE.Camera();
	scene.add(camera);

	var geometry = new THREE.BoxGeometry(1, 1, 1);
	var material = new THREE.MeshNormalMaterial({transparent: true, opacity: 0.5, side: THREE.DoubleSide});
	mesh = new THREE.Mesh(geometry, material);
	mesh.position.y = geometry.parameters.height / 2
	scene.add(mesh);

	var geometry = new THREE.TorusKnotGeometry(0.3, 0.1, 64, 16);
	var material = new THREE.MeshNormalMaterial();
	mesh = new THREE.Mesh(geometry, material);
	mesh.position.y = 0.5
	scene.add(mesh);

	scene.visible = false

	requestAnimationFrame(animate);
}

function onResize() 
{
	arToolkitSource.onResizeElement()
	arToolkitSource.copyElementSizeTo(renderer.domElement)
	if (window.arToolkitContext.arController !== null) {
		arToolkitSource.copyElementSizeTo(window.arToolkitContext.arController.canvas)
	}
}


function initARContext() 
{ // create atToolkitContext
	arToolkitContext = new THREEx.ArToolkitContext({
		cameraParametersUrl: "https://raw.githack.com/AR-js-org/AR.js/master/data/data/camera_para.dat",
		detectionMode: 'mono'
	})

	// initialize it
	arToolkitContext.init(() => { // copy projection matrix to camera
		camera.projectionMatrix.copy(arToolkitContext.getProjectionMatrix());
		arToolkitContext.arController.orientation = 'landscape';
		arToolkitContext.arController.options.orientation = 'landscape';
		console.log('arToolkitContext', arToolkitContext);
		window.arToolkitContext = arToolkitContext;
	})

	arMarkerControls = new THREEx.ArMarkerControls(arToolkitContext, camera, {
		type: 'pattern',
		patternUrl: 'https://raw.githack.com/AR-js-org/AR.js/master/data/data/patt.hiro',
		changeMatrixMode: 'cameraTransformMatrix'
	})

	console.log('ArMarkerControls', arMarkerControls);
	window.arMarkerControls = arMarkerControls;
}


function onReady() 
{
	arToolkitSource.domElement.addEventListener('canplay', () => {
		console.log("Камера працює");
		initARContext();
	});
	window.arToolkitSource = arToolkitSource;
	setTimeout(() => { onResize() }, 100);
}


function init_ar()
{
	arToolkitSource = new THREEx.ArToolkitSource({sourceType: 'webcam', sourceWidth: 640, sourceHeight: 480})

	arToolkitSource.init(onReady);

	window.addEventListener('resize', function () {
		onResize()
	})

}


function animate() 
{
	const delta=10*Math.PI/180;

	requestAnimationFrame(animate);

	if (!arToolkitContext || !arToolkitSource || !arToolkitSource.ready) {
		return;
	}

	arToolkitContext.update(arToolkitSource.domElement)

	// update scene.visible if the marker is seen
	scene.visible = camera.visible

	mesh.rotation.x += delta;
	renderer.render(scene, camera);
}

