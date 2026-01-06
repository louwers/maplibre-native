import org.gradle.api.Task
import org.gradle.kotlin.dsl.get
import org.gradle.external.javadoc.StandardJavadocDocletOptions

plugins {
    `maven-publish`
    id("com.android.library")
    id("maplibre.artifact-settings")
}

// Only apply this plugin if the publishToGitHub property is set
if (project.hasProperty("publishToGitHub") && project.property("publishToGitHub") == "true") {

    tasks.register<Javadoc>("androidJavadocs") {
        source = fileTree(android.sourceSets.getByName("main").java.srcDirs)
        classpath = files(android.bootClasspath)
        isFailOnError = false
    }

    tasks.register<Jar>("androidJavadocsJar") {
        archiveClassifier.set("javadoc")
        from(tasks.named("androidJavadocs", Javadoc::class.java).get().destinationDir)
    }

    tasks.register<Jar>("androidSourcesJar") {
        archiveClassifier.set("sources")
        from(android.sourceSets.getByName("main").java.srcDirs)
    }

    tasks.withType<Javadoc> {
        options.encoding = "UTF-8"
        (options as StandardJavadocDocletOptions).apply {
            charSet = "UTF-8"
            docEncoding = "UTF-8"
        }
    }

    artifacts {
        add("archives", tasks.named("androidSourcesJar"))
        add("archives", tasks.named("androidJavadocsJar"))
    }

    project.logger.lifecycle("GitHub Packages publishing enabled")
    
    // Override group ID and artifact ID if provided
    if (project.hasProperty("githubPackagesGroupId")) {
        group = project.property("githubPackagesGroupId") as String
    } else {
        group = project.extra["mapLibreArtifactGroupId"] as String
    }

    if (project.hasProperty("githubPackagesVersion")) {
        version = project.property("githubPackagesVersion") as String
    } else {
        version = project.extra["versionName"] as String
    }

    fun configureMavenPublicationGitHub(
        renderer: String,
        publicationName: String,
        artifactIdPostfix: String,
        descriptionPostfix: String,
        buildType: String = "Release"
    ) {
        publishing {
            repositories {
                maven {
                    name = "GitHubPackages"
                    url = uri("https://maven.pkg.github.com/${System.getenv("GITHUB_REPOSITORY") ?: "louwers/maplibre-native"}")
                    credentials {
                        username = System.getenv("GITHUB_ACTOR")
                        password = System.getenv("GITHUB_TOKEN")
                    }
                }
            }
            
            publications {
                create<MavenPublication>(publicationName) {
                    val baseArtifactId = if (project.hasProperty("githubPackagesArtifactId")) {
                        project.property("githubPackagesArtifactId") as String
                    } else {
                        project.extra["mapLibreArtifactId"] as String
                    }
                    
                    groupId = project.group.toString()
                    artifactId = "$baseArtifactId$artifactIdPostfix"
                    version = project.version.toString()

                    from(components["${renderer}${buildType}"])

                    pom {
                        name.set("${project.extra["mapLibreArtifactTitle"]}$descriptionPostfix")
                        description.set("${project.extra["mapLibreArtifactTitle"]}$descriptionPostfix")
                        url.set(project.extra["mapLibreArtifactUrl"].toString())
                        licenses {
                            license {
                                name.set(project.extra["mapLibreArtifactLicenseName"].toString())
                                url.set(project.extra["mapLibreArtifactLicenseUrl"].toString())
                            }
                        }
                        developers {
                            developer {
                                id.set(project.extra["mapLibreDeveloperId"].toString())
                                name.set(project.extra["mapLibreDeveloperName"].toString())
                                email.set("team@maplibre.org")
                            }
                        }
                        scm {
                            connection.set(project.extra["mapLibreArtifactScmUrl"].toString())
                            developerConnection.set(project.extra["mapLibreArtifactScmUrl"].toString())
                            url.set(project.extra["mapLibreArtifactUrl"].toString())
                        }
                    }
                }
            }
        }
    }

    afterEvaluate {
        configureMavenPublicationGitHub("opengl", "defaultrelease", "", "")
        configureMavenPublicationGitHub("opengl", "defaultdebug", "-debug", " (Debug)", "Debug")
        configureMavenPublicationGitHub("vulkan", "vulkanrelease", "-vulkan", " (Vulkan)")
        configureMavenPublicationGitHub("vulkan", "vulkandebug", "-vulkan-debug", " (Vulkan, Debug)", "Debug")
        configureMavenPublicationGitHub("opengl", "openglrelease", "-opengl", " (OpenGL ES)")
        configureMavenPublicationGitHub("opengl", "opengldebug", "-opengl-debug", " (OpenGL ES, Debug)", "Debug")
    }

    afterEvaluate {
        android.libraryVariants.forEach { variant ->
            tasks.named("androidJavadocs", Javadoc::class.java).configure {
                doFirst {
                    classpath = classpath.plus(files(variant.javaCompileProvider.get().classpath))
                }
            }
        }
    }
}
