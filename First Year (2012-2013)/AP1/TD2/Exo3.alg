algo exo3TD2

var
	entier note, somme, moyenne, C;

principal
debut

	#Saisie et initialisation des valeurs
	C := 0;
	somme := 0;
	saisir("Entrez une note:", @note);

	tantque (note <> (-1))

		si (note <= 20) alors

			si (note >= 0) alors
				C := C + 1;
				somme := somme + note;
				saisir("Entrez une note:", @note);
			sinon
				saisir("Entrez une note valide:", @note);
			finsi
		sinon
			saisir("Entrez une note valide:", @note);
		finsi

	fintantque

	afficher("La somme est " + somme);
	afficher(" et la moyenne est " + (somme/C));
	afficher(" .");
fin
