pipeline {
	agent {
		node {
			label 'x64 || rpi'
			customWorkspace '/home/jenkins/iot/Tle5012b'
		}
	}

	options {
		buildDiscarder(
			logRotator(
				numToKeepStr: '5',
				artifactNumToKeepStr: '5'
			)
		)
		disableConcurrentBuilds()
	}

	/*
	triggers {
		cron('H H(0-1) * * *')
	}
	*/

	stages {
		stage('Build documentation') {
			parallel {
				/*-----------------------------------------------------------------------------
				 * html
				 *-----------------------------------------------------------------------------
				 */
				stage('HTML') {
					steps {
						echo "html"
						//sh ("export DOXY_BIN_PATH=/usr/local/bin/;cd ${env.WORKSPACE}/docs;/usr/bin/make html")
					}
				}
				/*-----------------------------------------------------------------------------
				 * latex/pdf
				 *-----------------------------------------------------------------------------
				 */
				stage('PDF') {
					steps {
						echo "latex/pdf"
						/*
						sh ("export DOXY_BIN_PATH=/usr/local/bin/;cd ${env.WORKSPACE}/docs;/usr/bin/make pdf")
						build(
							job: 'dev/doxy_maker_pdf',
							propagate: true,
							parameters: [
								[
									$class: 'StringParameterValue',
									name: 'WORKSPACE',
									value: "${env.WORKSPACE}"
								],
							]
						)
						*/
					}
				}
			} // end parallel
		} // end docu build

		stage('Check') {
			steps {
				echo "check"
				sh "cd  ${env.WORKSPACE};mkdir -p build;/usr/local/bin/cppcheck -v --enable=all --xml-version=2 -I examples src 2> build/cppcheck-report.xml"
			} // end steps
		} // end stage

		stage('SonarQube') {
			environment {
				scannerHome = tool 'SonarQubeScanner'
			}
			steps {
				withSonarQubeEnv('SonarQube') {
					sh "export JAVA_HOME=/volume1/@appstore/java-installer/jdk-11;${scannerHome}/bin/sonar-scanner -X"
				}
				catchError(buildResult: 'SUCCESS', stageResult: 'FAILURE') {
					timeout(time: 10, unit: 'MINUTES') {
						waitForQualityGate abortPipeline: true
					}
				}
			} // end steps
		} // end stage

		stage('Build') {
			parallel {
				/*-----------------------------------------------------------------------------
				 * development
				 *-----------------------------------------------------------------------------
				 */
				stage('DEVELOPMENT') {
					steps {
						echo "html deploy"
						//sh ("mkdir -p /mnt/raspel/Public/doxygen/Tle5012/;cd ${env.WORKSPACE}/docs;cp -r html /mnt/raspel/Public/doxygen/Tle5012/")

					}
				}


				/*-----------------------------------------------------------------------------
				 * production
				 *-----------------------------------------------------------------------------
				 */
				stage('PRODUCTION') {
					steps {
						echo "Production"
						/*
						build(
							job: 'dev/I-Tec/CI-CD/task I-Tec grantDB',
							propagate: true,
							parameters: [
								[
									$class: 'StringParameterValue',
									name: 'RAZWARE_TIER',
									value: 'production'
								],
								[
									$class: 'StringParameterValue',
									name: 'RAZWEB_ROOT',
									value: '/home/razweb/htdocs-vihlarazweb1'
								],
								[
									$class: 'StringParameterValue',
									name: 'RAMEZ_ROOT_URL',
									value: 'https://vihlarazweb1.vih.infineon.com'
								]
							]
						)
						*/
					}
				}

			} // end parallel
		} // end stage
	} // end stages

	/*-----------------------------------------------------------------------------
	 * post
	 *-----------------------------------------------------------------------------
	 */
	post {
		failure {
			mail(
				to: 'olaf.filies@t-online.de',
				subject: "[EYENET JENKINS] TLE5012b pipeline:",
				body: "Something during Jenkins pipeline run went wrong."
			)
		}
	}

}
