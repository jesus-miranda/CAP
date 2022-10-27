#include <math.h>
#include "nbody.h"

void bodyForce(body p, float dt, int n) {

const int alignment=64;

	for (int i = 0; i < n; i++) { 
		float Fx = 0.0f; float Fy = 0.0f; float Fz = 0.0f;

		#pragma vector alligned
		for (int j = 0; j < n; j++) {
			if (i!=j) {
				const float dx = p.x[j] - p.x[i];
				const float dy = p.y[j] - p.y[i];
				const float dz = p.z[j] - p.z[i];
				//double softeningSquared = 1e-3;
				const float softeningSquared = 1e-3;
				const float distSqr = dx*dx + dy*dy + dz*dz + softeningSquared;
				const float invDist = 1.0f / sqrtf(distSqr);
				const float invDist3 = invDist * invDist * invDist;

				//double G = 6.674e-11;
				const float G = 6.674e-11;
				const float g_masses = G * p.m[j] * p.m[i];

				Fx += g_masses * dx * invDist3; 
				Fy += g_masses * dy * invDist3; 
				Fz += g_masses * dz * invDist3;
			}
		}

		p.vx[i] += dt*Fx/p.m[i]; p.vy[i] += dt*Fy/p.m[i]; p.vz[i] += dt*Fz/p.m[i];
	}
}

void integrate(body p, float dt, int n){
	for (int i = 0 ; i < n; i++) {
		p.x[i] += p.vx[i]*dt;
		p.y[i] += p.vy[i]*dt;
		p.z[i] += p.vz[i]*dt;
	}
}
