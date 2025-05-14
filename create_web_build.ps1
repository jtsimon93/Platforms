# Define the web build function
function Build-Web {
    Write-Host "Configuring and building web profile..."
    emcmake cmake -S . -B build_web -DCMAKE_BUILD_TYPE=Release
    cmake --build build_web
}

Build-Web
