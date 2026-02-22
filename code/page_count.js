// plain UMD, global `supabase`
const SUPABASE_URL = 'https://ndbofiopsoyvouktgyej.supabase.co';
const SUPABASE_KEY = 'sb_publishable_snLWhTe434QNCoZKAnUB3Q_xpvVD7PQ';
const supabaseClient = supabase.createClient(SUPABASE_URL, SUPABASE_KEY);

const counterEl = document.getElementById('visit-counter');

async function initCounter() {
	try {
		if (!sessionStorage.getItem('visited')) {
			await supabaseClient.rpc('increment_page_visit_counter');
			sessionStorage.setItem('visited', '1');
		}

		const { data: row, error } = await supabaseClient
			.from('page_visit_counter')
			.select('value')
			.eq('id', 1)
			.single();

		if (error) console.warn('Fetch error:', error);

		if (counterEl) counterEl.textContent = row?.value ?? 0;

	} catch (err) {
		console.error('Unexpected error:', err);
	}
}

document.addEventListener('DOMContentLoaded', initCounter);

document.getElementById('btn-gallery').addEventListener('click', () => {
	window.location.href = 'gallery';
});
document.getElementById('btn-journal').addEventListener('click', () => {
	window.location.href = 'journal';
});