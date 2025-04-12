#version 460

#define MAX_STEPS 100
#define MAX_DIST 100.0
#define SURFACE_DIST 0.01

layout(location = 0) out vec4 outColor;

vec2 resolution = vec2(1920.0, 1080.0);

float sdfSphere(vec3 p, float r) {
    return length(p) - r;
}

float sdfBox(vec3 p, vec3 b) {
    vec3 d = abs(p) - b;
    return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0);
}

float sceneSDF(vec3 p) {
    float d1 = sdfSphere(p - vec3(-1, 0, 0), 1.0);
    float d2 = sdfBox(p - vec3(1, 0, 0), vec3(1.0));
    return min(d1, d2);
}

float raymarch(vec3 ro, vec3 rd) {
    float t = 0.0;
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 p = ro + rd * t;
        float d = sceneSDF(p);
        if (d < SURFACE_DIST) return t;
        if (t > MAX_DIST) break;
        t += d;
    }
    return -1.0;
}

vec3 getNormal(vec3 p) {
    float eps = 0.001;
    return normalize(vec3(
        sceneSDF(p + vec3(eps, 0, 0)) - sceneSDF(p - vec3(eps, 0, 0)),
        sceneSDF(p + vec3(0, eps, 0)) - sceneSDF(p - vec3(0, eps, 0)),
        sceneSDF(p + vec3(0, 0, eps)) - sceneSDF(p - vec3(0, 0, eps))
    ));
}

vec3 shade(vec3 p, vec3 ro) {
    vec3 n = getNormal(p);
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.5));
    float diff = max(dot(n, lightDir), 0.0);
    return vec3(1.0, 0.8, 0.6) * diff;
}

void main() {
    // Screen space UV
    vec2 uv = (gl_FragCoord.xy / resolution) * 2.0 - 1.0;
    uv.x *= resolution.x / resolution.y;

    // Hardcoded camera
    vec3 camPos = vec3(5.0, 2.0, 5.0);
    vec3 camTarget = vec3(0.0, 0.0, 0.0);
    vec3 camDir = normalize(camTarget - camPos);
    vec3 camUp = vec3(0.0, 1.0, 0.0);
    vec3 camRight = normalize(cross(camDir, camUp));
    camUp = normalize(cross(camRight, camDir));

    float focalLength = 1.0;
    vec3 rayDir = normalize(uv.x * camRight + uv.y * camUp + focalLength * camDir);

    float t = raymarch(camPos, rayDir);
    vec3 color = vec3(0.0);

    if (t > 0.0) {
        vec3 p = camPos + rayDir * t;
        color = shade(p, camPos);
    }

    outColor = vec4(color, 1.0);
}
