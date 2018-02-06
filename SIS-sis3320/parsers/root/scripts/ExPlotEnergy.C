/* An example ROOT macro plotting the energy branch in a histogram
	 Load the macro using .L ExPlotEnergy in a ROOT session, then execute
	 the function below */
void ExPlotEnergy(string inFile) {
	TFile *f = new TFile(inFile.c_str(), "READ");
	TTree *t = (TTree*)f->Get("SISEvents");
	
	// Draw the tree, ROOT style, with a cut on channel 1
	// Sets up the bins and range in the first argument
	TCanvas *c = new TCanvas("cEnergy", "Energy Histogram", 800, 800);
	t->Draw("energy/16.0 >> hEnergy(4096, 0.0, 65535.0)", "channel == 1", "");
	TH1D *hEnergy = (TH1D*)gDirectory->Get("hEnergy");
	hEnergy->GetXaxis()->SetTitle("Energy (arb)");
	hEnergy->GetYaxis()->SetTitle("Counts");
	hEnergy->SetLineColor(kBlack);
	hEnergy->SetTitle("Energy Histogram");
	c->Update();

	return;
}
