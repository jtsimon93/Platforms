function Build-Web {
    Write-Host "Running the web build script..."
    & .\create_web_build.ps1
}

function Serve-Web {
    Write-Host "Serving web build..."
    # Start Python server in the build_web directory without changing the current shell directory
    Start-Process -NoNewWindow -FilePath "python" -ArgumentList "-m http.server 8080 --directory build_web"
}

function Open-Browser {
    Write-Host "Opening browser..."
    Start-Process "http://localhost:8080"
}

Build-Web
Open-Browser
Serve-Web