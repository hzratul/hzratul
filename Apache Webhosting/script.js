const starsContainer = document.querySelector('.stars');

function createStar() {
    const star = document.createElement('div');
    star.classList.add('star');
    
    // Random position
    const x = Math.random() * window.innerWidth;
    const y = Math.random() * window.innerHeight;
    
    // Random size (between 1px and 3px)
    const size = Math.random() * 2 + 1;
    
    // Random glow duration (between 1s and 3s)
    const duration = (Math.random() * 2 + 1).toFixed(2);
    
    // Apply styles
    star.style.left = `${x}px`;
    star.style.top = `${y}px`;
    star.style.width = `${size}px`;
    star.style.height = `${size}px`;
    star.style.setProperty('--duration', `${duration}s`);
    
    starsContainer.appendChild(star);
}

function createStars(numStars) {
    for (let i = 0; i < numStars; i++) {
        createStar();
    }
}

// Create 200 stars
createStars(200);