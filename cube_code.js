var scene, camera, renderer;

var arToolkitSource, arToolkitContext;

function onResize()
{
	arToolkitSource.onResizeElement()	
	arToolkitSource.copyElementSizeTo(renderer.domElement)	
	if ( arToolkitContext.arController !== null )
		arToolkitSource.copyElementSizeTo(arToolkitContext.arController.canvas)	
}


function init()
{
	scene = new THREE.Scene();

	let ambientLight = new THREE.AmbientLight( 0xcccccc, 0.5 );
	scene.add( ambientLight );
				
	camera = new THREE.Camera();
	scene.add(camera);

	renderer = new THREE.WebGLRenderer({antialias : true, alpha: true});
	
	var WIDTH = window.innerWidth, HEIGHT = window.innerHeight; // визначити розміри вікна
	renderer.setSize(WIDTH, HEIGHT); // масштабування холсту до розміру вікна

	document.body.appendChild( renderer.domElement );

	// setup arToolkitSource

	arToolkitSource = new THREEx.ArToolkitSource({sourceType : 'webcam'});

	arToolkitSource.init(onResize);
	
	// handle resize event
	window.addEventListener('resize', onResize);
	
	// create atToolkitContext
	arToolkitContext = new THREEx.ArToolkitContext({
		cameraParametersUrl: 'https://raw.githubusercontent.com/AR-js-org/AR.js/master/data/data/camera_para.dat',
		detectionMode: 'mono'
	});
	
	// copy projection matrix to camera when initialization complete
	arToolkitContext.init( function onCompleted(){
		camera.projectionMatrix.copy( arToolkitContext.getProjectionMatrix() );
	});

	// build markerControls
	markerRoot1 = new THREE.Group();
	scene.add(markerRoot1);

	let markerControls1 = new THREEx.ArMarkerControls(arToolkitContext, markerRoot1, {
		type: 'pattern', patternUrl: "https://raw.githubusercontent.com/AR-js-org/AR.js/master/data/data/patt.hiro",
	})

	let geometry1	= new THREE.BoxGeometry(1,1,1);
	let material1	= new THREE.MeshNormalMaterial({
		transparent: true,
		opacity: 0.5,
		side: THREE.DoubleSide
	}); 
	
	mesh1 = new THREE.Mesh( geometry1, material1 );
	mesh1.position.y = 0.5;
	
	markerRoot1.add( mesh1 );

	// build markerControls
	markerRoot2 = new THREE.Group();
	scene.add(markerRoot2);

	let markerControls2 = new THREEx.ArMarkerControls(arToolkitContext, markerRoot2, {
		type: 'pattern', patternUrl: "https://raw.githubusercontent.com/AR-js-org/AR.js/master/data/multimarkers/multi-abcdef/patt.a",
	})

	const geometry2 = new THREE.SphereGeometry( 0.5, 32, 16 );
	const material2 = new THREE.MeshBasicMaterial( { color: 0xffff00 } );
	const sphere = new THREE.Mesh( geometry2, material2 );
	scene.add( sphere );
	
	sphere.position.y = 0.5;
	
	markerRoot2.add( sphere );
	
	const geometry3 = new THREE.TorusGeometry(0.5, 0.03, 16, 100 );
	const material3 = new THREE.MeshBasicMaterial( { color: 0xffff00 } );
	torus = new THREE.Mesh( geometry3, material3 );
	scene.add( torus );
	torus.position.y = 0.5;
	torus.position.x = 1.5;
	
	markerRoot2.add( torus );
	
}



function animate()
{
	requestAnimationFrame(animate);
	if ( arToolkitSource.ready !== false )
		arToolkitContext.update( arToolkitSource.domElement );
	renderer.render( scene, camera );
	torus.rotation.x+=0.1;
}

