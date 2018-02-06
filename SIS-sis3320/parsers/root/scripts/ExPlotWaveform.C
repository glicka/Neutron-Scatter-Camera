/* An example ROOT macro plotting the waveform for a single event
	 Load the macro using .L ExPlotWaveform in a ROOT session, then execute
	 the function below */
void ExPlotWaveform(string inFile, int nEvent) {
	TFile *f = new TFile(inFile.c_str(), "READ");
	TTree *t = (TTree*)f->Get("SISEvents");
	vector<int> *raw = new vector<int>;
	t->SetBranchAddress("raw", &raw);
	t->GetEntry(nEvent);

	TH1D *hRaw = new TH1D("hRaw", "Raw Waveform", raw->size(), 0.0,raw->size()-1);
	// There is, in theory, a way to do it with TTree::Draw() but it's completely
	// unintuitive. Even a 65000 sample event shouldn't take long :)
	for (int i=0;i < raw->size();i++) {
		hRaw->Fill(i, raw->at(i));
	}
	hRaw->GetXaxis()->SetTitle("Sample #");
	hRaw->GetYaxis()->SetTitle("ADC Value");
	TCanvas *c = new TCanvas("cRaw", "Raw Waveform", 800, 800);
	hRaw->Draw();
	delete raw;
	return;
}
