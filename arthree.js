function initscene()
{
		// init renderer
		renderer = new THREE.WebGLRenderer({antialias: true, alpha: true});
		renderer.setSize(window.innerWidth, window.innerHeight);
		document.body.appendChild(renderer.domElement);

		// init scene and camera
		scene = new THREE.Scene();

		// Create a camera
		camera = new THREE.Camera();
		scene.add(camera);

		// add a torus knot
		var geometry = new THREE.BoxGeometry(1,1,1);
		var material = new THREE.MeshNormalMaterial({
			transparent: true,
			opacity: 0.5,
			side: THREE.DoubleSide
		});
		mesh = new THREE.Mesh(geometry, material);
		mesh.position.y = geometry.parameters.height / 2;
		//mesh.position.x=-1;
		//mesh.position.y=3;
		scene.add(mesh);

		geometry = new THREE.TorusKnotGeometry(0.3, 0.1, 64, 16);
		material = new THREE.MeshNormalMaterial();
		mesh = new THREE.Mesh(geometry, material);
		mesh.position.y = 0.5;
		scene.add(mesh);
}


function onResize() {
			arToolkitSource.onResizeElement()
			arToolkitSource.copyElementSizeTo(renderer.domElement)
			if (window.arToolkitContext.arController !== null) {
				arToolkitSource.copyElementSizeTo(window.arToolkitContext.arController.canvas)
			}
}


function onReady() {
			arToolkitSource.domElement.addEventListener('canplay', () => {
				console.log('Камера працює');
				initARContext();
			});

			window.arToolkitSource = arToolkitSource;
			setTimeout(() => {
				onResize()
			}, 50);
}


function initARContext() { // create atToolkitContext
			arToolkitContext = new THREEx.ArToolkitContext({
				cameraParametersUrl: 'https://raw.githack.com/AR-js-org/AR.js/master/data/data/camera_para.dat',
				detectionMode: 'mono'})

			// initialize it
			arToolkitContext.init(() => { // copy projection matrix to camera
				camera.projectionMatrix.copy(arToolkitContext.getProjectionMatrix());

				arToolkitContext.arController.orientation = 'landscape';//getSourceOrientation();
				arToolkitContext.arController.options.orientation = 'landscape';//getSourceOrientation();

				//console.log('arToolkitContext', arToolkitContext);
				window.arToolkitContext = arToolkitContext;
			})

			// MARKER
			arMarkerControls = new THREEx.ArMarkerControls(arToolkitContext, camera, {
				type: 'pattern',
				patternUrl: "https://raw.githack.com/AR-js-org/AR.js/master/three.js/examples/marker-training/examples/pattern-files/pattern-letterA.patt",
				changeMatrixMode: 'cameraTransformMatrix'
			})

			scene.visible = false

			//console.log('ArMarkerControls', arMarkerControls);
			window.arMarkerControls = arMarkerControls;
}

function initcamera()
{
		arToolkitContext=arToolkitSource=false;
		arToolkitSource.ready=false;

		arToolkitSource = new THREEx.ArToolkitSource({sourceType: 'webcam', sourceWidth: 640, sourceHeight: 480})

		arToolkitSource.init(onReady)

		// handle resize
		window.addEventListener('resize', function () {
			onResize()
		})
}


function animate() {
			requestAnimationFrame(animate);

			if (!arToolkitContext || !arToolkitSource || !arToolkitSource.ready) {
				return;
			}

			arToolkitContext.update(arToolkitSource.domElement)

			// update scene.visible if the marker is seen
			scene.visible = camera.visible

			mesh.rotation.x += Math.PI * 0.01; // delta
			renderer.render(scene, camera);
}


